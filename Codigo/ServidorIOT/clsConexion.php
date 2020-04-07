<?php
    class clsConexion{
        public static function Conectar(){
            define('servidor', 'localhost');
            define('nombre_bd', 'db_arduino');
            define('usuario', 'root');
            define('password', 'Tavohgo12345');	
            $opciones = array(PDO::MYSQL_ATTR_INIT_COMMAND => 'SET NAMES utf8');			
            try{
                $conexion = new PDO("mysql:host=".servidor."; dbname=".nombre_bd, usuario, password, $opciones);
                return $conexion;
            }catch (Exception $e){
                die("El error de Conexión es: ". $e->getMessage());
            }
        }
    }
?>