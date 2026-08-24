
using Estructura_Datos.PILA;

Pila<int> pila = new Pila<int>();

pila.Push(10);
pila.Push(20);
pila.Push(30);

Console.WriteLine("Elemento superior"+pila.Peek());
Console.WriteLine("Elemento eliminado"+pila.Pop());
Console.WriteLine("Elemento superior despues del Pop"+pila.Peek());
Console.WriteLine("Tamaño de la Pila: "+ pila.Tamaño());