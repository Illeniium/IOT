<?php

    include_once 'clsConexion.php';    
    $objeto = new clsConexion();
    $conexion = $objeto->Conectar();
    $sql = "";

    if(isset($_GET['OPCION'])){

        $OPCION = $_GET['OPCION'];

        switch ($OPCION) {
            case 1:
                 
                $serie = $_POST['txtSerie'];
                $luminosidad = $_POST['txtLuminosidad'];
                
                $sql = " ALTER TABLE tbl_luminosidad AUTO_INCREMENT = 1 ";	
                $resultado = $conexion->prepare($sql);
                $resultado->execute();
        
                $sql = " INSERT INTO tbl_luminosidad VALUES (null, CURRENT_TIMESTAMP, '$serie', '$luminosidad') ";		
                $resultado = $conexion->prepare($sql);
                $resultado->execute(); 
                
                $sql = " UPDATE tbl_configuracion SET vchEstado = '$luminosidad' WHERE intID = 5 ";		
                $resultado = $conexion->prepare($sql);
                $resultado->execute();   

            break;
            case 2:
                 
                $serie = $_POST['txtSerie'];
                $temperatura = $_POST['txtTemperatura'];
                
                $sql = " ALTER TABLE tbl_temperatura AUTO_INCREMENT = 1 ";	
                $resultado = $conexion->prepare($sql);
                $resultado->execute();
        
                $sql = " INSERT INTO tbl_temperatura VALUES (null, CURRENT_TIMESTAMP, '$serie', '$temperatura') ";		
                $resultado = $conexion->prepare($sql);
                $resultado->execute(); 
                
                $sql = " UPDATE tbl_configuracion SET vchEstado = '$temperatura' WHERE intID = 3 ";		
                $resultado = $conexion->prepare($sql);
                $resultado->execute();   

            break;
            case 3:

                $serie = $_POST['txtSerie'];
                $humedad = $_POST['txtHumedad'];

                $sql = " ALTER TABLE tbl_humedad AUTO_INCREMENT = 1 ";	
                $resultado = $conexion->prepare($sql);
                $resultado->execute();
        
                $sql = " INSERT INTO tbl_humedad VALUES (null, CURRENT_TIMESTAMP, '$serie', '$humedad') ";
	
                $resultado = $conexion->prepare($sql);
                $resultado->execute(); 
                
                $sql = " UPDATE tbl_configuracion SET vchEstado = '$humedad' WHERE intID = 4 ";		
                $resultado = $conexion->prepare($sql);
                $resultado->execute(); 

            break;
            case 4:

                $serie = $_POST['txtSerie'];
                $distancia = $_POST['txtDistancia'];

                $sql = " ALTER TABLE tbl_distancia AUTO_INCREMENT = 1 ";	
                $resultado = $conexion->prepare($sql);
                $resultado->execute();
        
                $sql = " INSERT INTO tbl_distancia VALUES (null, CURRENT_TIMESTAMP, '$serie', '$distancia') ";
	
                $resultado = $conexion->prepare($sql);
                $resultado->execute(); 
                
                $sql = " UPDATE tbl_configuracion SET vchEstado = '$distancia' WHERE intID = 6 ";		
                $resultado = $conexion->prepare($sql);
                $resultado->execute(); 

            break;
            case 5:

                $distancia = $_POST['txtDistancia'];
                
                $sql = " UPDATE tbl_configuracion SET vchEstado = '$distancia' WHERE intID = 2 ";		
                $resultado = $conexion->prepare($sql);
                $resultado->execute(); 

                header("Location:index.php");

            break;
            case 6:

                //MOSTRAR LUMINOCIDAD
                $consulta = "SELECT * FROM tbl_configuracion WHERE intID = 5 ";
                $resultado = $conexion->prepare($consulta);
                $resultado->execute();
                $data = $resultado->fetchAll(PDO::FETCH_ASSOC);
                foreach($data as $dat){
                    echo $dat['vchEstado'];
                }

            break;
            case 7:
                
                //MOSTRAR TEMPERATURA
                $consulta = "SELECT * FROM tbl_configuracion WHERE intID = 3 ";
                $resultado = $conexion->prepare($consulta);
                $resultado->execute();
                $data = $resultado->fetchAll(PDO::FETCH_ASSOC);
                foreach($data as $dat){
                    echo $dat['vchEstado'];
                }

            break;
            case 8:

                //MOSTRAR HUMEDAD
                $consulta = "SELECT * FROM tbl_configuracion WHERE intID = 4 ";
                $resultado = $conexion->prepare($consulta);
                $resultado->execute();
                $data = $resultado->fetchAll(PDO::FETCH_ASSOC);
                foreach($data as $dat){
                    echo $dat['vchEstado'];
                }

            break;
            case 9:

                //MOSTRAR DISTANCIA
                $consulta = "SELECT * FROM tbl_configuracion WHERE intID = 6 ";
                $resultado = $conexion->prepare($consulta);
                $resultado->execute();
                $data = $resultado->fetchAll(PDO::FETCH_ASSOC);
                foreach($data as $dat){
                    echo $dat['vchEstado'];
                }

            break;
            case 10:

                //MOSTRAR DISTANCIA LED
                $consulta = "SELECT * FROM tbl_configuracion WHERE intID = 2 ";
                $resultado = $conexion->prepare($consulta);
                $resultado->execute();
                $data = $resultado->fetchAll(PDO::FETCH_ASSOC);
                foreach($data as $dat){
                    echo $dat['vchEstado'];
                }

            break;
            case 11:

                //MOSTRAR SERVO
                $consulta = "SELECT * FROM tbl_configuracion WHERE intID = 1 ";
                $resultado = $conexion->prepare($consulta);
                $resultado->execute();
                $data = $resultado->fetchAll(PDO::FETCH_ASSOC);
                foreach($data as $dat){
                    echo $dat['vchEstado'];
                }

            break;            
        }

    }

?>

