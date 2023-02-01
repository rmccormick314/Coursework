/*
Title:             AppointmentsOverlap
Desc:              Determines whether two appointments will overlap
Files:             AppointmentsOverlap.java
Semester:          Fall 2019
Author name:          Richard McCormick
Author email:    rlm443@nau.edu
Class section:       01
*/

package appointmentsoverlap;

import java.util.Scanner;

public class AppointmentsOverlap {
        public static void main(String[]args){
            int[] appointmentOne = new int[2];
            int[] appointmentTwo = new int[2];
            
            Scanner scanner = new Scanner(System.in);
            System.out.println("Appointment One starts at: ");
            appointmentOne[0] = scanner.nextInt();
            System.out.println("Appointment One ends at: ");
            appointmentOne[1] = scanner.nextInt();
            
            System.out.println("Appointment Two starts at: ");
            appointmentTwo[0] = scanner.nextInt();
            System.out.println("Appointment Two ends at: ");
            appointmentTwo[1] = scanner.nextInt();
            
            if (appointmentTwo[0] <= appointmentOne[1]){
                System.out.print("The appointments overlap.");
            }
            else{
                System.out.println("The appoints do not overlap.");
            }
    

        }
}
