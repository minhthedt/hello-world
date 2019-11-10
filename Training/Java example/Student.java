package com.example;
import  com.example.People;
public class Student extends People {  
	private String subject;
    public Student(String name,int age,String subject){  
     super(name,age);
	 this.subject = subject;
    }  
}  