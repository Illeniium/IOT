<!DOCTYPE html>
<html lang="en">

<head>
    <!-- Required meta tags-->
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta name="description" content="au theme template">
    <meta name="author" content="Hau Nguyen">
    <meta name="keywords" content="au theme template">

    <!-- Title Page-->
    <title>Arduino</title>

    <!-- Fontfaces CSS-->
    <link href="css/font-face.css" rel="stylesheet" media="all">
    <link href="vendor/font-awesome-4.7/css/font-awesome.min.css" rel="stylesheet" media="all">
    <link href="vendor/font-awesome-5/css/fontawesome-all.min.css" rel="stylesheet" media="all">
    <link href="vendor/mdi-font/css/material-design-iconic-font.min.css" rel="stylesheet" media="all">

    <!-- Bootstrap CSS-->
    <link href="vendor/bootstrap-4.1/bootstrap.min.css" rel="stylesheet" media="all">

    <!-- Vendor CSS-->
    <link href="vendor/animsition/animsition.min.css" rel="stylesheet" media="all">
    <link href="vendor/bootstrap-progressbar/bootstrap-progressbar-3.3.4.min.css" rel="stylesheet" media="all">
    <link href="vendor/wow/animate.css" rel="stylesheet" media="all">
    <link href="vendor/css-hamburgers/hamburgers.min.css" rel="stylesheet" media="all">
    <link href="vendor/slick/slick.css" rel="stylesheet" media="all">
    <link href="vendor/select2/select2.min.css" rel="stylesheet" media="all">
    <link href="vendor/perfect-scrollbar/perfect-scrollbar.css" rel="stylesheet" media="all">

    <!-- Main CSS-->
    <link href="css/theme.css" rel="stylesheet" media="all">

    <!-- Jquery JS-->
    <script src="vendor/jquery-3.2.1.min.js"></script>

</head>

<body style="background-color: #E5E5E5;" class="animsition">
    <div class="page-wrapper">
        <div class="page-content--bge5">
            <div class="container">
                <div class="login-wrap">
                    <div id="aplication" class="login-content">
                        <div class="login-titulo">
                            <p>
                                Arduino
                            </p>
                        </div><br>
                        <div class="login-form">
                            <div action="clsArduino.php?OPCION=1" method="post">
                                <div class="form-group">
                                    <label>LUMINUCIDAD</label>
                                    <p id="RLUMINUCIDAD"></p>
                                </div>
                                <div class="form-group">
                                    <label>TEMPERATURA</label>
                                    <p id="RTEMPERATURA"></p>
                                </div>
                                <div class="form-group">
                                    <label>HUMEDAD</label>
                                    <p id="RHUMEDAD"></p>
                                </div>
                                <div class="form-group">
                                    <label>DISTANCIA</label>
                                    <p id="RDISTANCIA"></p>
                                </div>
                                <div class="form-group">
                                    <label>DISTANCIA DEL LED</label>
                                    <p id="RDISTANCIALED"></p>
                                </div>
                                <form action="clsArduino.php?OPCION=5" method="post">
                                    <div class="form-group">
                                        <label>DEFINIR DISTANCIA</label>
                                        <input v-model="txtDistanciaLed" class="au-input au-input--full" type="text" id="txtDistancia" name="txtDistancia" placeholder="Distancia" autocomplete="off">
                                    </div>
                                    <label v-if=" txtDistanciaLed === ''" class="au-input au-input--full" style="text-align: center; background-color: coral; color: white;">Tienes que llenar los campos para poder enviar los datos</label>
                                    <div v-else>
                                        <button onclick="" class="au-btn au-btn--block au-btn--green m-b-20" type="submit">
                                            <i class="fa fa-paper-plane"></i>&nbsp; Enviar</button>
                                    </div>
                                </form>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        <script src="vue.js"></script>
        <script>
            var app = new Vue({
                el:'#aplication',
                data:{
                    txtDistanciaLed:'',
                }
            });
        </script>
        <script type="text/javascript">
            $(document).ready(function(){
                setInterval(
                    function(){
                        $('#RLUMINUCIDAD').load('clsArduino.php?OPCION=6');
                    },200
                );
            });

            $(document).ready(function(){
                setInterval(
                    function(){
                        $('#RTEMPERATURA').load('clsArduino.php?OPCION=7');
                    },200
                );
            });

            $(document).ready(function(){
                setInterval(
                    function(){
                        $('#RHUMEDAD').load('clsArduino.php?OPCION=8');
                    },200
                );
            });

            $(document).ready(function(){
                setInterval(
                    function(){
                        $('#RDISTANCIA').load('clsArduino.php?OPCION=9');
                    },200
                );
            });

            $(document).ready(function(){
                setInterval(
                    function(){
                        $('#RDISTANCIALED').load('clsArduino.php?OPCION=10');
                    },200
                );
            });
        </script>
    </div>

    <!-- Jquery JS-->
    <script src="vendor/jquery-3.2.1.min.js"></script>
    <!-- Bootstrap JS-->
    <script src="vendor/bootstrap-4.1/popper.min.js"></script>
    <script src="vendor/bootstrap-4.1/bootstrap.min.js"></script>
    <!-- Vendor JS       -->
    <script src="vendor/slick/slick.min.js">
    </script>
    <script src="vendor/wow/wow.min.js"></script>
    <script src="vendor/animsition/animsition.min.js"></script>
    <script src="vendor/bootstrap-progressbar/bootstrap-progressbar.min.js">
    </script>
    <script src="vendor/counter-up/jquery.waypoints.min.js"></script>
    <script src="vendor/counter-up/jquery.counterup.min.js">
    </script>
    <script src="vendor/circle-progress/circle-progress.min.js"></script>
    <script src="vendor/perfect-scrollbar/perfect-scrollbar.js"></script>
    <script src="vendor/chartjs/Chart.bundle.min.js"></script>
    <script src="vendor/select2/select2.min.js">
    </script>
    <!-- -->     
    <!-- Main JS-->
    <script src="js/main.js"></script>

</body>

</html>
<!-- end document-->