class Person{
   void print(){
	System.out.println("Person__>void print(){}");
    }
/*    public void fun(){
	this.print();	
    }
*/
}

class Student extends Person{
   protected void print(){
        System.out.println("Student__>void print(){}");
    }
 /*   public void fun(){
        this.print();
    }
*/
}
public class ExampleDemo01{
	public static void main(String args[]){
		new Student().print();
	}
}
