-- init-db/init.sql
-- Ejecutado automáticamente por la imagen oficial de Postgres al inicializar la BD.

-- -------------------------
-- Extensiones (si necesarias)
-- -------------------------

-- -------------------------
-- Schemas / Users (opcional)
-- -------------------------
-- Puedes crear un rol dedicado: ya estamos usando POSTGRES_USER vía docker env
-- (dejamos esto comentado si prefieres usar el usuario por defecto).

-- -------------------------
-- Tablas principales
-- -------------------------
/* Users */
CREATE TABLE IF NOT EXISTS users (
    id SERIAL PRIMARY KEY,
    username VARCHAR(100) UNIQUE NOT NULL,
    password_u VARCHAR(200) NOT NULL,
    created_at TIMESTAMP WITH TIME ZONE DEFAULT now(),
    updated_at TIMESTAMP WITH TIME ZONE DEFAULT now()
);
/* Donantes */
CREATE TABLE IF NOT EXISTS donantes (
    id SERIAL PRIMARY KEY,
    nombre VARCHAR(200) NOT NULL,
    apellido VARCHAR(200),
    email VARCHAR(200),
    telefono VARCHAR(50),
    direccion TEXT,
    tipo_documento VARCHAR(50),
    numero_documento VARCHAR(100),
    created_at TIMESTAMP WITH TIME ZONE DEFAULT now(),
    updated_at TIMESTAMP WITH TIME ZONE DEFAULT now()
);

/* Beneficiarios */
CREATE TABLE IF NOT EXISTS beneficiarios (
    id SERIAL PRIMARY KEY,
    nombre VARCHAR(200) NOT NULL,
    apellido VARCHAR(200),
    referencia TEXT, -- ej. organización, familia, etc.
    direccion TEXT,
    telefono VARCHAR(50),
    created_at TIMESTAMP WITH TIME ZONE DEFAULT now(),
    updated_at TIMESTAMP WITH TIME ZONE DEFAULT now()
);

/* Tipos de donación (alimento, ropa, dinero, insumo, etc.) */
CREATE TABLE IF NOT EXISTS tipos_donacion (
    id SERIAL PRIMARY KEY,
    codigo VARCHAR(50) UNIQUE NOT NULL,
    descripcion VARCHAR(200) NOT NULL
);

/* Inventario: items almacenados */
CREATE TABLE IF NOT EXISTS inventario (
    id SERIAL PRIMARY KEY,
    tipo_id INT REFERENCES tipos_donacion(id) ON DELETE SET NULL,
    descripcion TEXT,
    cantidad NUMERIC(12,2) DEFAULT 0,
    unidad VARCHAR(50),
    ubicacion VARCHAR(200),
    estado VARCHAR(50) DEFAULT 'disponible', -- disponible, reservado, dañado
    created_at TIMESTAMP WITH TIME ZONE DEFAULT now(),
    updated_at TIMESTAMP WITH TIME ZONE DEFAULT now()
);

/* Donaciones recibidas */
CREATE TABLE IF NOT EXISTS donaciones_recibidas (
    id SERIAL PRIMARY KEY,
    donante_id INT REFERENCES donantes(id) ON DELETE SET NULL,
    inventario_id INT REFERENCES inventario(id) ON DELETE SET NULL, --
    descripcion TEXT,
    cantidad NUMERIC(12,2) DEFAULT 1,
    unidad VARCHAR(50), -- ej. kg, unidades, litros
    estado VARCHAR(50) DEFAULT 'registrada', -- registrada, al_inventario, entregada
    fecha_donacion TIMESTAMP WITH TIME ZONE DEFAULT now(),
    recibidor VARCHAR(200), -- quien recibió físicamente
    created_at TIMESTAMP WITH TIME ZONE DEFAULT now(),
    updated_at TIMESTAMP WITH TIME ZONE DEFAULT now()
);

/* Donaciones enviadas (distribuciones) */
CREATE TABLE IF NOT EXISTS donaciones_enviadas (
    id SERIAL PRIMARY KEY,
    beneficiario_id INT REFERENCES beneficiarios(id) ON DELETE SET NULL,
    inventario_id INT REFERENCES inventario(id) ON DELETE SET NULL,
    descripcion TEXT,
    cantidad NUMERIC(12,2) DEFAULT 1,
    unidad VARCHAR(50),
    fecha_envio TIMESTAMP WITH TIME ZONE DEFAULT now(),
    remitente VARCHAR(200), -- quien entregó
    estado VARCHAR(50) DEFAULT 'enviado', -- enviado, recibido_confirmado
    created_at TIMESTAMP WITH TIME ZONE DEFAULT now(),
    updated_at TIMESTAMP WITH TIME ZONE DEFAULT now()
);

-- -------------------------
-- Triggers para mantener updated_at
-- -------------------------
CREATE OR REPLACE FUNCTION set_updated_at_column()
RETURNS TRIGGER AS $$
BEGIN
   NEW.updated_at = now();
   RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_donantes_update BEFORE UPDATE ON donantes
FOR EACH ROW EXECUTE PROCEDURE set_updated_at_column();
CREATE TRIGGER trg_beneficiarios_update BEFORE UPDATE ON beneficiarios
FOR EACH ROW EXECUTE PROCEDURE set_updated_at_column();
CREATE TRIGGER trg_dr_update BEFORE UPDATE ON donaciones_recibidas
FOR EACH ROW EXECUTE PROCEDURE set_updated_at_column();
CREATE TRIGGER trg_de_update BEFORE UPDATE ON donaciones_enviadas
FOR EACH ROW EXECUTE PROCEDURE set_updated_at_column();
CREATE TRIGGER trg_inv_update BEFORE UPDATE ON inventario
FOR EACH ROW EXECUTE PROCEDURE set_updated_at_column();
-- ===========================================================
-- FUNCIONES PARA ACTUALIZAR INVENTARIO AUTOMÁTICAMENTE
-- ===========================================================

-- Cuando se recibe una donación: sumar o crear en inventario
CREATE OR REPLACE FUNCTION add_to_inventory_from_donacion_recibida()
RETURNS TRIGGER AS $$
DECLARE
    stock_actual NUMERIC;
BEGIN
    IF NEW.inventario_id IS NULL THEN
        RAISE NOTICE 'No se especificó inventario_id, no se actualiza inventario.';
        RETURN NEW;
    END IF;

    SELECT cantidad INTO stock_actual FROM inventario WHERE id = NEW.inventario_id;

    IF stock_actual IS NULL THEN
        RAISE EXCEPTION 'El producto con id % no existe en inventario', NEW.inventario_id;
    END IF;

    UPDATE inventario
    SET cantidad = cantidad + NEW.cantidad,
        updated_at = now()
    WHERE id = NEW.inventario_id;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;


-- Cuando se envía una donación: restar del inventario
CREATE OR REPLACE FUNCTION remove_from_inventory_from_donacion_enviada()
RETURNS TRIGGER AS $$
DECLARE
    stock_actual NUMERIC;
BEGIN
    IF NEW.inventario_id IS NULL THEN
        RAISE NOTICE 'No se especificó inventario_id, no se actualiza inventario.';
        RETURN NEW;
    END IF;

    SELECT cantidad INTO stock_actual FROM inventario WHERE id = NEW.inventario_id;

    IF stock_actual IS NULL THEN
        RAISE EXCEPTION 'El producto con id % no existe en inventario', NEW.inventario_id;
    END IF;

    IF stock_actual < NEW.cantidad THEN
        RAISE EXCEPTION 'No hay suficiente stock en inventario para el item con id % (disponible: %, solicitado: %)',
            NEW.inventario_id, stock_actual, NEW.cantidad;
    END IF;

    UPDATE inventario
    SET cantidad = cantidad - NEW.cantidad,
        updated_at = now()
    WHERE id = NEW.inventario_id;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;
-- ===========================================================
-- TRIGGERS QUE USAN LAS FUNCIONES
-- ===========================================================

-- Cuando se registra una donación recibida, agregar automáticamente al inventario
CREATE TRIGGER trg_add_to_inventory_after_insert
AFTER INSERT ON donaciones_recibidas
FOR EACH ROW
EXECUTE PROCEDURE add_to_inventory_from_donacion_recibida();

CREATE TRIGGER trg_remove_from_inventory_after_insert
AFTER INSERT ON donaciones_enviadas
FOR EACH ROW
EXECUTE PROCEDURE remove_from_inventory_from_donacion_enviada();

-- -------------------------
-- Índices útiles
-- -------------------------
CREATE INDEX IF NOT EXISTS idx_donaciones_recibidas_fecha ON donaciones_recibidas(fecha_donacion);
CREATE INDEX IF NOT EXISTS idx_donaciones_enviadas_fecha ON donaciones_enviadas(fecha_envio);
CREATE INDEX IF NOT EXISTS idx_inventario_tipo ON inventario(tipo_id);

-- -------------------------
-- DATOS INICIALES EXTENDIDOS
-- -------------------------
INSERT INTO users (username, password_u) VALUES
('admin', 'admin')
ON CONFLICT (username) DO NOTHING;
-- Tipos de donación (ya definidos arriba, se reafirman por si falta alguno)
INSERT INTO tipos_donacion (codigo, descripcion) VALUES
('ALIM','Alimento'),
('ROPA','Ropa'),
('INSU','Insumos/Higiene'),
('DIN','Dinero/Efectivo'),
('JUG','Juguetes'),
('MED','Medicinas'),
('ESC','Útiles Escolares')
ON CONFLICT (codigo) DO NOTHING;

-- -------------------------
-- Donantes (personas u organizaciones)
-- -------------------------
INSERT INTO donantes (nombre, apellido, email, telefono, direccion, tipo_documento, numero_documento) VALUES
('Juan', 'Perez', 'juan.perez@example.com', '+51912345678', 'Calle Falsa 123, Arequipa', 'DNI', '12345678'),
('Ana', 'Lopez', 'ana.lopez@example.com', '+51988888888', 'Av. Las Flores 456, Lima', 'DNI', '87654321'),
('Carlos', 'Ramirez', 'carlos.ramirez@example.com', '+51977777777', 'Jr. Libertad 789, Cusco', 'DNI', '56781234'),
('Fundación Esperanza', NULL, 'contacto@esperanza.org', '+51955555555', 'Av. Central 101, Trujillo', 'RUC', '20512345678'),
('Empresa Solidaria SAC', NULL, 'donaciones@solidaria.pe', '+51944444444', 'Calle Comercio 55, Piura', 'RUC', '20678901234'),
('Lucia', 'Gomez', 'lucia.gomez@example.com', '+51999999999', 'Mz A Lt 2, Arequipa', 'DNI', '65432109'),
('Pedro', 'Vega', 'pedro.vega@example.com', '+51912398765', 'Calle Real 321, Tacna', 'DNI', '44556677');

-- -------------------------
-- Beneficiarios (personas o instituciones receptoras)
-- -------------------------
INSERT INTO beneficiarios (nombre, apellido, referencia, direccion, telefono, created_at) VALUES
('Maria', 'Gonzales', 'Centro Comunitario A', 'Av. Principal 456, Lima', '+51987654321', now() - INTERVAL '1 month'),
('Hogar San Juan', NULL, 'Hogar de niños', 'Calle Esperanza 12, Arequipa', '+51910101010', now() - INTERVAL '2 month'),
('Comedor Santa Rosa', NULL, 'Comedor popular', 'Av. Las Palmeras 34, Trujillo', '+51911111111', now() - INTERVAL '3 month'),
('Asociación Luz Verde', NULL, 'Apoyo a adultos mayores', 'Av. Grau 555, Cusco', '+51922222222', now() - INTERVAL '4 month'),
('Luis', 'Molina', 'Familia en situación vulnerable', 'Calle 9 de Octubre 56, Piura', '+51933333333', now() - INTERVAL '5 month'),
('Colegio San Pablo', NULL, 'Institución educativa', 'Jr. Los Héroes 120, Lima', '+51944444444', now() - INTERVAL '6 month'),
('Centro Médico Vida', NULL, 'Atención médica gratuita', 'Av. Salaverry 100, Tacna', '+51955555555', now() - INTERVAL '7 month');

-- -------------------------
-- Inventario inicial (stock disponible)
-- -------------------------
INSERT INTO inventario ( tipo_id, descripcion, cantidad, unidad, ubicacion, estado) VALUES
( 1, 'Arroz', 100, 'kg', 'Almacén Central', 'disponible'),
( 1, 'Conservas de atún', 200, 'unidades', 'Almacén Central', 'disponible'),
(2, 'Polos de algodón', 150, 'unidades', 'Almacén Central', 'disponible'),
( 3, 'Papel higiénico paquete x4', 80, 'paquetes', 'Almacén Central', 'disponible'),
( 4, 'Donación monetaria general', 1500, 'PEN', 'Cuenta bancaria', 'disponible'),
( 5, 'Muñecos y peluches', 90, 'unidades', 'Almacén Central', 'disponible'),
( 6, 'Medicamentos básicos', 60, 'cajas', 'Farmacia interna', 'disponible'),
( 7, 'Cuadernos escolares', 300, 'unidades', 'Almacén Central', 'disponible');

-- -------------------------
-- Donaciones recibidas (estas además dispararán el trigger y sumarán al inventario)
-- -------------------------
INSERT INTO donaciones_recibidas (
    donante_id, inventario_id, descripcion, cantidad, unidad, recibidor, estado, fecha_donacion
) VALUES
(1, 1, 'Fideos 1kg', 50, 'kg', 'Pedro Ramos', 'registrada', now() - interval '10 days'),
(2, 3, 'Abrigos de invierno', 30, 'unidades', 'Carla Torres', 'registrada', now() - interval '8 days'),
(3, 4, 'Kits de limpieza', 40, 'paquetes', 'Jose Diaz', 'registrada', now() - interval '6 days'),
(4, 1, 'Arroz kg', 25, 'kg', 'Lucia Herrera', 'registrada', now() - interval '5 days'),
(5, 6, 'Juguetes varios', 60, 'unidades', 'Mario Peña', 'registrada', now() - interval '4 days'),
(6, 8, 'Útiles escolares básicos', 120, 'unidades', 'Luisa Campos', 'registrada', now() - interval '3 days'),
(7, 7, 'Medicinas básicas', 40, 'cajas', 'Fernando Ruiz', 'registrada', now() - interval '2 days');

-- -------------------------
-- Donaciones enviadas
-- -------------------------
INSERT INTO donaciones_enviadas (
    beneficiario_id, inventario_id, descripcion, cantidad, unidad, remitente, estado, fecha_envio
) VALUES
(1, 1, 'Arroz kg', 20, 'kg', 'Pedro Ramos', 'enviado', now() - interval '2 days'),
(2, 3, 'Abrigos de invierno', 10, 'unidades', 'Carla Torres', 'enviado', now() - interval '1 days'),
(3, 4, 'Kits de limpieza', 5, 'paquetes', 'Jose Diaz', 'enviado', now() - interval '1 days'),
(4, 7, 'Medicamentos básicos', 10, 'cajas', 'Luis Romero', 'enviado', now() - interval '1 days'),
(5, 8, 'Útiles escolares básicos', 30, 'unidades', 'Ana Torres', 'enviado', now() - interval '12 hours');