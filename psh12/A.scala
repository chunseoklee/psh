//import scala.collection.mutable.ArrayBuffer

object A {
 def main(args: Array[String]) = {
   val N = readLine.toInt;
   val slist = readLine.split(" ");
   val ilist = (for (i <- 0 until N) yield slist(i).toInt).toArray;
   
   var min = 1001;
   val s = ilist(0);
   val t = ilist(N-1);
   for (i <- 0 until N-2){
     if(ilist(i+1) < ilist(i+2)){
       if(min > ilist(i+2)){
	 min = ilist(i+2);
       }
     }
     else {
       if(min > ilist(i+1)){
	 min = ilist(i+1);
       }
     }
   }
   if(min > s || min > t){
     println(math.min(s,t));
   }
   else{
     println(min);
   }
 }   
}
