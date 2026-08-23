using System;

namespace Estructura_Datos.COLA
{
    public class Paquete
    {
        public int Id { get; set; }
        public int TamañoBytes { get; set; }
        public long TimestampMs { get; set; }

        public Paquete(int id, int tamañoBytes, long timestampMs)
        {
            Id = id;
            TamañoBytes = tamañoBytes;
            TimestampMs = timestampMs;
        }

    }
public enum EstadoPaquete
    {
        Aceptado,
        RechazadoPorTasa,
        RechazadoPorBufferLleno
    }
}