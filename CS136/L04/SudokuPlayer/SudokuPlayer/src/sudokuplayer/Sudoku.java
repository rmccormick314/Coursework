package sudokuplayer;
import java.util.ArrayList;

/*
 *Title:          	Sudoku
 * Desc:          	Generates game of Sudoku, checks to see whether the game
 *                	is valid if the player follows the typical rules of Sudoku
 * Files:         	Sudoku.java, SudokuPlayer.java
 * Semester:      	Fall 2019
 * Author 1:      	Isabel Salazar
 * Author 1 Email:	is356@nau.edu
 * Author 2:      	Richard McCormick
 * Author 2 Email:	rlm443@nau.edu
 * Lab Section:   	CS136L- Section 003
 */

public class Sudoku {
	private char[][] board;
	Sudoku(){
    	board = new char[9][9];
    	for(int row =0; row <9 ; row++){
        	for(int col =0; col <9 ; col++){
            	board[row][col] = ' ';
        	}
    	}
   	 
	}
    
	Sudoku(String start){
    	board = new char[9][9];
    	int index =0;
   	 
    	for(int row =0; row <9 ; row++){
        	for(int col =0; col <9 ; col++){
            	board[row][col] = start.charAt(index);
            	index++;
        	}
        	index++;
    	}
   	 
	}
	 
	char getSquare(int row, int col){
     	return board[row][col];
 	}
    
	void setSquare(int row, int col, char value){
    	board[row][col] = value;
	}
    
	boolean rowValid(){
    	for(int row = 0; row < 9; row++){
        	String checkList = "";
        	for(int col = 0; col < 9; col++){
            	char current = board[row][col];
            	if (checkList.contains(""+current)){
                	return false;
            	}
            	else {
                	checkList += current;
            	}   
        	}
    	}
    	return true;
	}
    
	boolean colValid(){
    	for(int col = 0; col < 9; col++){
        	String checkList = "";
        	for(int row = 0; row < 9; row++){
            	char current = board[row][col];
            	if (checkList.contains(""+current)){
                	return false;
            	}
            	else {
                	checkList += current;
            	}   
        	}
    	}
    	return true;
	}
    
	boolean squareValid(){
   	 
   	 
    	for (int i = 0; i <= 6; i += 3){
        	for (int j = 0; j <= 6; j += 3){
            	String checkList = "";
            	for (int row = 0 + i; row < 3 + i; row++){
                	for (int col = 0+j; col < 3+j; col++){
                    	char current = board[row][col];
                    	if (checkList.contains(""+current)){
                        	return false;
                    	}
                    	else {
                        	checkList += current;
                    	}  
                   	 
                	}
            	}
        	}
    	}
	return true;
	}
    
	boolean isValid(){
    	boolean result = true;
    	if(rowValid() && colValid() && squareValid()){
       	 
    	}
    	else{
        	result = false;
    	}
    	return result;
	}
    
	boolean isSolved(){
    	for(int row =0; row <9 ; row++){
        	for(int col =0; col <9 ; col++){
            	if (board[row][col] == ' '){
                	return false;
            	}
        	}
    	}
    	return isValid();
	}
}
