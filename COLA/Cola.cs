using System;
using System.Collections.Generic;

namespace Estructura_Datos.COLA
{
    public class Cola<T>
    {
        private readonly List<T> elementos = new List<T>();

        public int Count => elementos.Count;

        public void Enqueue(T item)
        {
            elementos.Add(item);
        }

        public T Dequeue()
        {
            if (IsEmpty())
                throw new InvalidOperationException("La cola está vacía.");

                T item = elementos[0];
                elementos.RemoveAt(0);
                return item;
            
        }

        public T Peek()
        {
            if (IsEmpty())
                throw new InvalidOperationException("La cola está vacía.");
            
            return elementos[0];
        }

        public bool IsEmpty() => elementos.Count == 0;

        public List<T> ObtenerElementos() => new List<T>(elementos);
    }
}