namespace Estructura_Datos.PILA
{
    public class Pila<T>{
        private List<T> elementos;
    public Pila(){
            elementos = new List<T>();
        }

    //Sirve para que metamos un elemento a la pila
    public void Push(T elementos){
            elementos.Add(elementos);
        }

    //Saca el ultimo elemento de la pila
    //este es fundamental para implementar el UNDO
    public T Pop(){
           if(elementos.Count == 0)
            {
                throw new InvalidOperationException("La Pila esta vacia.");
            }

        T elemento = elementos [elementos.Count-1];
        elementos.RemoveAt(elementos.Count-1);
        return elemento;
        }

    //Mira el ultimo elemento de la pila pero no lo saca
    public T Peek(){
        if(elementos.Count == 0){
                throw new InvalidOperationException("La pila esta vacia.");
            }
        return elementos [elementos.Count-1];
        }


    //Nos dice si la pila esta vacia, nos ayuda cuando se haga un UNDO y todavia no exista una operacion para deshacer
    public bool EstaVacia(){
            return elementos.Count == 0;
        }

    //Nos dice cuantos elemtos hay en la pila
    public int Tamaño(){
            return elementos.Count;
        }

    //Vacia la pila completamente, nos va a ayudar cuando utilicemos REDO
    public void Limpiar(){
            elementos.Clear();
        }
    }
}