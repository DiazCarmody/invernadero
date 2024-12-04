<?php
// El JSON que recibes del Arduino
$json_data = '{"temperatura":25.1,"humedad":59.1}';

// Decodificar el JSON a un array asociativo
$data = json_decode($json_data, true);

// Mostrar los datos en HTML
echo "Temperatura: " . $data['temperatura'] . "°C<br>";
echo "Humedad: " . $data['humedad'] . "%";
?>
