<?php
session_start();  // Asegúrate de iniciar la sesión al principio

// Depuración: Ver todos los valores de sesión
var_dump($_SESSION);

$temperatura = isset($_SESSION['temperatura']) ? $_SESSION['temperatura'] : 'indefinido';
$humedad = isset($_SESSION['humedad']) ? $_SESSION['humedad'] : 'indefinido';
$numero = isset($_SESSION['numero']) ? $_SESSION['numero'] : 'No definido';
?>
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <title>Estado del sistema</title>
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
</head>
<body>
    <div class="container">
        <table>
            <tr>
                <th>Parámetro</th>
                <th>Estado</th>
            </tr>
            <tr>
                <td>Temperatura</td>
                <td id="temperatura"><?php echo $temperatura; ?> °C</td>
            </tr>
            <tr>
                <td>Humedad</td>
                <td id="humedad"><?php echo $humedad; ?> %</td>
            </tr>
            <tr>
                <td>Número</td>
                <td><?php echo $numero; ?></td>
            </tr>
        </table>
    </div>
</body>
</html>
