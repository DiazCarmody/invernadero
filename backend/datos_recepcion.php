<?php
session_start();  // Asegúrate de iniciar la sesión al principio del archivo

if ($_SERVER['REQUEST_METHOD'] == 'POST' || $_SERVER['REQUEST_METHOD'] == 'GET') {
    require_once('../backend/main.php');

    // Obtener los datos del POST
    $temperatura = isset($_GET['temperatura']) ? (float) $_GET['temperatura'] : null;
    $humedad = isset($_GET['humedad']) ? (float) $_GET['humedad'] : null;

    // Almacenar en sesión
    $_SESSION['temperatura'] = $temperatura;
    $_SESSION['humedad'] = $humedad;
    $_SESSION['numero'] = 2;  // Establecer la variable numero

    // Debugging: Verifica que la sesión se está guardando correctamente
    var_dump($_SESSION);

    // Respuesta al cliente
    echo json_encode([
        'temperatura' => $temperatura !== null ? $temperatura : "No disponible",
        'humedad' => $humedad !== null ? $humedad : "No disponible",
        'numero' => $_SESSION['numero']
    ]);
} else {
    echo json_encode(['error' => 'Método no permitido']);
}
