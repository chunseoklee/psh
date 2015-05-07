object A {
  def apo[A, B](v: B)(f: B => Option[(A, Either[B, List[A]])]): List[A] = f(v) match {
   case None => Nil
   case Some((a, Left(b)))   => a :: apo(b)(f)
   case Some((a, Right(as))) => a :: as 
}

  def interleave[A](period: Int, substitutes: List[A], elems: List[A]): List[A] =
    apo((period, substitutes, elems)){
      case (_, _, Nil)       => None
      case (_, Nil, v :: vs) => Some((v, Right(vs)))
      case (0, x :: xs, vs)  => Some((x, Left((period, xs, vs))))
      case (n, xs, v :: vs)  => Some((v, Left((n - 1, xs, vs))))  
    }

  def main(args: Array[String]) = {
    val input = readLine.split(" ").map(_.toInt).toList;
    val n = input(0);
    val m = input(1);
    val l = (for (i <- 1 to m) yield i).toList; 
    val (first,rest) = l.splitAt(m/2);
    val order = if (m%2 == 0) {
      interleave(1,(first.reverse) , rest);
    } 
    else {
      rest.head::interleave(1,first.reverse , rest.tail);
    }
    
    println((order));
  }
}
