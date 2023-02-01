public interface ListIterator<T> {

    /**
     * Tests whether there are elements remaining in the list in the forward
     * direction. In other words, next() will not fail with a
     * NoSuchElementException.
     *
     * @return true if the list continues in the forward direction
     */
    boolean hasNext();

    /**
     * Tests whether there are elements remaining in the list in the reverse
     * direction. In other words, previous() will not fail with a
     * NoSuchElementException.
     *
     * @return true if the list continues in the reverse direction
     */
    boolean hasPrevious();

    /**
     * Obtain the next element in the list in the forward direction. Repeated
     * calls to next may be used to iterate over the entire list, or calls to
     * next and previous may be used together to go forwards and backwards.
     * Alternating calls to next and previous will return the same element.
     *
     * @return the next element in the list in the forward direction
     * @throws NoSuchElementException if there are no more elements
     */
    T next();

    /**
     * Obtain the next element in the list in the reverse direction. Repeated
     * calls to previous may be used to iterate backwards over the entire list,
     * or calls to next and previous may be used together to go forwards and
     * backwards. Alternating calls to next and previous will return the same
     * element.
     *
     * @return the next element in the list in the reverse direction
     * @throws NoSuchElementException if there are no more elements
     */
    T previous();

    /**
     * Insert an element into the list at the current position of the iterator
     * The element is inserted in between the element that would be returned by
     * previous and the element that would be returned by next. After the
     * insertion, a subsequent call to next is unaffected, but a call to
     * previous returns the item that was added.
     *
     * @param o the object to insert into the list
     *
     */
    void add(T o);

    /**
     * Remove from the list the element last returned by a call to next or
     * previous. This method may only be called if neither add nor remove have
     * been called since the last call to next or previous.
     *
     * @throws IllegalStateException if neither next or previous have been
     * called, or if add or remove has been called since the last call to next
     * or previous
     *
     */
    void remove();

    /**
     * Replace the element last returned by a call to next or previous with a
     * given object. This method may only be called if neither add nor remove
     * have been called since the last call to next or previous.
     *
     * @param o the object to replace the element with
     * @throws IllegalStateException if neither next or previous have been
     * called, or if add or remove has been called since the last call to next
     * or previous
     *
     */
    void set(T o);

}
