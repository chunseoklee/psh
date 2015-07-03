let inf = 123456789


let explode s =
  let rec exp i l =
    if i < 0 then l else exp (i - 1) (s.[i] :: l) in
  exp (String.length s - 1) []
;;


let solve clist =
  let rec aux cl rfacc racc num=
  match cl with
  | [] -> List.append rfacc racc;
  | hd::tl when (hd == 'l') -> aux tl rfacc (num::racc) (num+1);
  | hd::tl when (hd == 'r') -> aux tl (num::rfacc) racc (num+1);
  in
  aux clist [] [] 1;
;;

let str = read_line ()
let () = ( print_string (solve (explode str)); print_newline () )
