object A {
<<<<<<< HEAD

=======
>>>>>>> 1d033b589c435c6a18cee19dc276deeb50855b5a
  def main(args: Array[String]) = {
    val input = readLine.split(" ").map(_.toInt).toList;
    val n = input(0);
    val m = input(1);
    //val l = (for (i <- 1 to m) yield i).toList; 
    //val (first,rest) = l.splitAt(m/2);
<<<<<<< HEAD

    val start = m/2;
    val sum = m+1;
    for (i <- 0 until (n/2+1)) {
      if(n == 0){
        ;
      }
      else if(m%2 == 0) {
        println(start-(i%start));
        if(i != (n/2) || n%2 == 0){ 
          println(sum - start + (i%start));
        }
      }
      else {
        if( i==0 || ((i-1)*2+1)%m == 0){
          println(start+1);
        }
        else {
          println(start-((i-1)%start));
          if ( i*2 + 1 <= n  ) {
            println(sum - start + ((i-1)%start));
          }
        }
      }
    }
    
=======
    var order = new Array[Int](m);
    if(m%2 == 0){
      for (i <- 0 until m/2)  {
	order(i*2) = m/2 - i;
	order(i*2+1) = m/2 + i + 1;
      }	   
    }
    else {
      order(0) = m/2 + 1;
      for (i <- 0 until m/2)  {
	order(i*2+1) = (m+1)/2-(i+1);
	order(i*2+2) = (m+1)/2 +(i+1);
      }	
    }
    
    for(i<-0 until n) {
      println(order(i%m))
    }
>>>>>>> 1d033b589c435c6a18cee19dc276deeb50855b5a
  }
}
