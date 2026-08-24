using System;

namespace Estructura_Datos.COLA
{
    public class Firewall
    {
        private readonly Cola<Paquete> bufferRecepcion = new Cola<Paquete>();
        private readonly Cola<long> colaTimestamps = new Cola<long>();


        public int CapacidadMaxBytes { get; private set; }
        public long VentanaTiempoMs { get; private set; }
        public int LimitePaquetes { get; private set; }

        public int BytesOcupados { get; private set;} = 0;

        public Firewall(int capacidadMaxBytes, long ventanaTiempoMs, int limitePaquetes)
        {
            CapacidadMaxBytes = capacidadMaxBytes;
            VentanaTiempoMs = ventanaTiempoMs;
            LimitePaquetes = limitePaquetes;
        }

        public EstadoPaquete ProcesarPaquete(Paquete paquete)
        {
            PurgarTimestampsExpirados(paquete.TimestampMs);

            if (colaTimestamps.Count >= LimitePaquetes)
            {
                return EstadoPaquete.RechazadoPorTasa;
            }

            if (BytesOcupados + paquete.TamañoBytes > CapacidadMaxBytes)
            {
                return EstadoPaquete.RechazadoPorBufferLleno;
            }

            bufferRecepcion.Enqueue(paquete);
            colaTimestamps.Enqueue(paquete.TimestampMs);
            BytesOcupados += paquete.TamañoBytes;

            return EstadoPaquete.Aceptado;
        }

        public Paquete? DesencolarPaquete()
        {
            if (bufferRecepcion.IsEmpty()) return null;

            Paquete p = bufferRecepcion.Dequeue();
            BytesOcupados -= p.TamañoBytes;
            return p;
        }

        private void PurgarTimestampsExpirados(long timestampActualMs)
        {
            while (!colaTimestamps.IsEmpty() && (timestampActualMs - colaTimestamps.Peek() > VentanaTiempoMs))
            {
                colaTimestamps.Dequeue();
            }
        }

        public Cola<Paquete> ObtenerBuffer() => bufferRecepcion;
        public Cola<long> ObtenerTimestamps() => colaTimestamps;

        
    }
}