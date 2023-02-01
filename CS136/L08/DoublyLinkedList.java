import java.util.NoSuchElementException;
import java.lang.IndexOutOfBoundsException;

public class DoublyLinkedList<T>{

  Node first;
  Node last;

  public void DoublyLinkedList(){
    Node first = null;
    Node last = null;
  }

  public class Node{
    public T data;
    public Node next;
    public Node previous;

    public void Node(){
      data = null;
      next = null;
      previous = null;
    }

  }

  public class DoublyListIterator implements ListIterator<T>{

    Node current = first;

    public void DoublyListIterator(){}

    public boolean hasNext(){
      return current.next != null;
    }

    public boolean hasPrevious(){
      return current.previous != null;
    }

    public T next(){
      if (!hasNext()){
        throw new NoSuchElementException();
      }
      else{
        current = current.next;
        return current.data;
      }
    }

    public T previous(){
      if (!hasPrevious()){
        throw new NoSuchElementException();
      }
      else{
        current = current.previous;
        return current.data;
      }
    }

    public void add(T element){
      if(current == null || current.previous == null){
        addFirst(element);
      }
      else{
        Node newNode = new Node();
        newNode.data = element;
        Node last = current.previous;
        last.next = newNode;
        newNode.previous = last;
        newNode.next = current;
        current.previous = newNode;
      }
    }

    public void remove(){
      if(current == null){
        throw new IllegalStateException();
      }
      if(current == first){
        removeFirst();
      }
      else{
        Node last = current.previous;
        Node successive = current.next;
        last.next = current.next;
        successive.previous = current.previous;
      }
    }

    public void set(T o){
      current.previous.data = o;
    }
  }

  public void addFirst(T value){
    Node newNode = new Node();
    newNode.data = value;
    newNode.next = first;
    first = newNode;
    if(last == null){
      last = first;
    }
  }

  public void addLast(T value){
    Node newNode = new Node();
    last.next = newNode;
    newNode.data = value;
    newNode.previous = last;
    last = newNode;
    if(first == null){
      first = last;
    }
  }

  public String toString(){
    String returnString = "[";
    Node current = first;
    while(current.next != null){
        returnString += current.data + ", ";
        current = current.next;
    }
    returnString += current.data + "]";
    return returnString;
  }

  public void removeFirst(){
    if(first == null){
      throw new NoSuchElementException();
    }
    else{
      first = first.next;
      first.previous = null;
    }
  }

  public void removeLast(){
    if(last == null){
      throw new NoSuchElementException();
    }
    else{
      last = last.previous;
      last.next = null;
    }
  }

  public T getLast(){
    if(last == null){
      throw new NoSuchElementException();
    }
    else{
      return last.data;
    }
  }

  public T getFirst(){
    if(first == null){
      throw new NoSuchElementException();
    }
    else{
      return first.data;
    }
  }

  public int size(){
    if(first == null){
      return 0;
    }
    else{
      int number = 1; // Count the first/current node
      Node current = first;
      while(current.next != null){
        number++;
        current = current.next;
      }
      return number;
    }
  }

  public T get(int index){
    Node current = first;
    for(int i = 0; i < index; i++){
      if(current.next == null){
        throw new IndexOutOfBoundsException("Index: " + index + ",  Size: " + (i+1));
      }
      current = current.next;
    }
    return current.data;
  }

  public int indexOf(T value){
    int number = 0;
    Node current = first;
    while(current.data != value){
      if(current.next == null){
        return -1;
      }
      number ++;
      current = current.next;
    }
    return number;
  }

  public ListIterator<T> listIterator(){
    ListIterator<T> iterator = new DoublyListIterator();
    return iterator;
  }
}
