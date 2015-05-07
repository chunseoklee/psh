object A {
  def main(args: Array[String]) = {
    val a = readLine.split(" ");
    val b = a.map(_.toInt).toList;
    b.reverse.foreach(println);
  }
}
