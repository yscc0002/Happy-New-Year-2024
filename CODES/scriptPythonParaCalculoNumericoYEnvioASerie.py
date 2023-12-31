"""
  Copyright (c) 2023 [Yoel Castillo]
 
  Este código ha sido escrito por mí, Yoel Castillo, para que lo uses de manera libre.
  He dedicado horas y horas a su creación, así que por favor, aprovéchalo.
  No se requiere atribución ni se impone ninguna restricción. Disfrútalo y úsalo bien.
"""

import serial
import time
from datetime import datetime

def esBisiesto(ano):
    if (ano % 4 == 0 and ano % 100 != 0) or (ano % 100 == 0 and ano % 400 == 0):
        return True
    else:
        return False

# HABLA CON ARDUINO
arduino = serial.Serial('COM4', 9600)
time.sleep(2)  # POR SI ACASO

while True:

    # TIMESTAMP DEL INICIO DEL AÑO 2023
    hoy = datetime.now()
    inicio2023 = datetime(2023, 1, 1)
    tiempoPasadoEnSegundos = hoy.timestamp() - inicio2023.timestamp()

    # CUANTOS SEGUNDOS TIENE EL ANO ACTUAL
    segundosTotalesDelAno = 31622400 if esBisiesto(hoy.year) else 31536000

    # CALCULA EL PROGRESO NUMERICO
    progresoNumerico = (tiempoPasadoEnSegundos/segundosTotalesDelAno) * 100

    # PREPARANDO Y ENVIANDO MENSAJE PARA EL PUERTO DEL ARDUINO (STRING)
    mensaje = f"{progresoNumerico}\n"
    arduino.write(mensaje.encode())

    time.sleep(2)
