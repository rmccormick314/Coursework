
public class DoublyLinkedListApp {

    static void Test1() { // Tests addFirst, addLast and toString
        DoublyLinkedList<Integer> list = new DoublyLinkedList<Integer>(); //Creates a linked list
        list.addFirst(3); // adds an element
        list.addLast(1); // adds an element
        list.addLast(2); // adds an element
        list.addLast(4); // adds an element
        System.out.println(list); // Should print [3, 1, 2, 4]
    }

    static void Test2() { // Tests addFirst, addLast, getFirst and getLast
        DoublyLinkedList<Integer> list = new DoublyLinkedList<Integer>(); //Creates a linked list
        list.addFirst(3); // adds an element
        list.addLast(1); // adds an element
        list.addLast(2); // adds an element
        list.addLast(4); // adds an element

        System.out.println(list.getFirst()); // Should print 3
        System.out.println(list.getLast()); // Should print 4
    }

    static void Test3() { // Tests addFirst, addLast, removeFirst and removeLast
        DoublyLinkedList<Integer> list = new DoublyLinkedList<Integer>(); //Creates a linked list
        list.addFirst(3); // adds an element
        list.addLast(1); // adds an element
        list.addLast(2); // adds an element
        list.addLast(4); // adds an element

        System.out.println(list); // Should print [3, 1, 2, 4]

        list.removeFirst();
        System.out.println(list); // Should print [1, 2, 4]

        list.removeLast();
        System.out.println(list); // Should print [1, 2]
    }

    static void Test4() { // Tests addFirst, addLast, removeFirst, removeLast and size
        DoublyLinkedList<Integer> list = new DoublyLinkedList<Integer>(); //Creates a linked list
        System.out.println("Size: " + list.size()); // Should print Size: 0

        list.addFirst(3); // adds an element
        list.addLast(1); // adds an element
        list.addLast(2); // adds an element
        list.addLast(4); // adds an element

        System.out.println(list); // Should print [3, 1, 2, 4]
        System.out.println("Size: " + list.size()); // Should print Size: 4

        list.removeFirst();
        System.out.println(list); // Should print [1, 2, 4]
        System.out.println("Size: " + list.size()); // Should print Size: 3

        list.removeLast();
        System.out.println(list); // Should print [1, 2]
        System.out.println("Size: " + list.size()); // Should print Size: 2
    }

    static void Test5() { // Tests addFirst, addLast, get, and indexOf
        DoublyLinkedList<Integer> list = new DoublyLinkedList<Integer>(); //Creates a linked list
        list.addFirst(3); // adds an element
        list.addLast(1); // adds an element
        list.addLast(2); // adds an element
        list.addLast(4); // adds an element

        System.out.println(list.get(3)); //Should print 4
        System.out.println(list.indexOf(3)); //Should print 0
        System.out.println(list.indexOf(13)); //Should print -1
    }

    static void Test6() { // Tests addFirst, addLast and get
        DoublyLinkedList<Integer> list = new DoublyLinkedList<Integer>(); //Creates a linked list
        list.addFirst(3); // adds an element
        list.addLast(1); // adds an element
        list.addLast(2); // adds an element
        list.addLast(4); // adds an element

        System.out.println(list.get(6)); //Should throw IndexOutOfBoundsException: Index: 6, Size: 4
    }

    static void Test7() { // Tests addFirst, addLast, hasNext and hasPrevious
        DoublyLinkedList<Integer> list = new DoublyLinkedList<Integer>(); //Creates a linked list
        list.addFirst(3); // adds an element
        list.addLast(1); // adds an element
        list.addLast(2); // adds an element
        list.addLast(4); // adds an element

        ListIterator<Integer> iter = list.listIterator(); //Retrieves an iterator for the list

        System.out.println(iter.hasNext()); //Should print true
        System.out.println(iter.hasPrevious()); //Should print false

    }

    static void Test8() { // Tests addFirst, addLast, next, previous and add
        DoublyLinkedList<Integer> list = new DoublyLinkedList<Integer>(); //Creates a linked list
        list.addFirst(3); // adds an element
        list.addLast(1); // adds an element
        list.addLast(2); // adds an element
        list.addLast(4); // adds an element

        ListIterator<Integer> iter = list.listIterator(); //Retrieves an iterator for the list

        System.out.println(iter.next()); //Should print 3
        System.out.println(iter.next()); //Should print 1
        System.out.println(iter.previous()); //Should print 1

        iter.add(5);

        System.out.println(list); // Should print [3, 5, 1, 2, 4]
    }

    static void Test9() { // Tests addFirst, addLast, next and set
        DoublyLinkedList<Integer> list = new DoublyLinkedList<Integer>(); //Creates a linked list
        list.addFirst(3); // adds an element
        list.addLast(1); // adds an element
        list.addLast(2); // adds an element
        list.addLast(4); // adds an element

        ListIterator<Integer> iter = list.listIterator(); //Retrieves an iterator for the list

        System.out.println(iter.next()); //Should print 3
        System.out.println(iter.next()); //Should print 1

        iter.set(5);

        System.out.println(list); // Should print [3, 5, 2, 4]
    }

    static void Test10() { // Tests addFirst, addLast, next and remove
        DoublyLinkedList<Integer> list = new DoublyLinkedList<Integer>(); //Creates a linked list
        list.addFirst(3); // adds an element
        list.addLast(1); // adds an element
        list.addLast(2); // adds an element
        list.addLast(4); // adds an element

        ListIterator<Integer> iter = list.listIterator(); //Retrieves an iterator for the list

        System.out.println(iter.next()); //Should print 3
        System.out.println(iter.next()); //Should print 1

        iter.remove();

        System.out.println(list); // Should print [3, 2, 4]
    }

    static void Test11() { // Tests addFirst, addLast, and previous
        DoublyLinkedList<Integer> list = new DoublyLinkedList<Integer>(); //Creates a linked list
        list.addFirst(3); // adds an element
        list.addLast(1); // adds an element
        list.addLast(2); // adds an element
        list.addLast(4); // adds an element

        ListIterator<Integer> iter = list.listIterator(); //Retrieves an iterator for the list

        iter.previous(); //Should throw NoSuchElementException excpetion
    }

    static void Test12() { // Tests addFirst, addLast, and next
        DoublyLinkedList<Integer> list = new DoublyLinkedList<Integer>(); //Creates a linked list
        list.addFirst(3); // adds an element
        list.addLast(1); // adds an element
        list.addLast(2); // adds an element
        list.addLast(4); // adds an element

        ListIterator<Integer> iter = list.listIterator(); //Retrieves an iterator for the list

        System.out.println(iter.next()); //Should print 3
        System.out.println(iter.next()); //Should print 1
        System.out.println(iter.next()); //Should print 2
        System.out.println(iter.next()); //Should print 4
        iter.next(); //Should throw NoSuchElementException excpetion
    }

    public static void main(String[] args) {
        Test1();
        Test2();
        Test3();
        Test4();

    }

}
