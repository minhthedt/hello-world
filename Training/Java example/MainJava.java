package com.example;
import com.example.People;

public class MainJava{  
    public static void main(String args[]){ 
	 People p = new People("vvthe",30);
     System.out.println("People: ");  
	 System.out.println("  name = " + p.getName());
	 System.out.println("  age  = " + p.getAge());
    }  
}  