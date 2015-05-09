object A {
  def main(args: Array[String]) = {
    val input = readLine.split(" ").map(_.toInt).toList;
    val n = input(0);
    val m = input(1);
    //val l = (for (i <- 1 to m) yield i).toList; 
    //val (first,rest) = l.splitAt(m/2);
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
  }
}
