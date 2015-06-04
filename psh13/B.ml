let explode s =
  let rec exp i l =
    if i < 0 then l else exp (i - 1) (s.[i] :: l) in
  exp (String.length s - 1) []
;;

let count4 num = 
  let rec aux n c = 
	match n with
	| [] -> c
	| hd::tl -> if hd == '4' then aux tl (c+1) else aux tl c
  in
  aux num 0
;;

let count7 num = 
  let rec aux n c = 
	match n with
	| [] -> c
	| hd::tl -> if hd == '7' then aux tl (c+1) else aux tl c
  in
  aux num 0
;;


let solve num = 
  let n4 = count4 num in
  let n7 = count7 num in
  if n4 == 0 && n7 == 0 
  then (-1) 
  else 
    if n7 > n4 then 7 else 4 
;;

let isthrow str= Str.string_match (Str.regexp ".*throw") str 0
;;
let istry str= Str.string_match (Str.regexp ".*try") str 0
;;
let iscatch str= Str.string_match (Str.regexp ".*catch") str 0
;;
    
  
let step line =
  if isthrow line then Printf.printf "%s\n" line
  else if istry line then Printf.printf "%s\n" line
  else if iscatch line then Printf.printf "%s\n" line
;;


(*main start*)		      
let n = read_int ()
;;		 
try
  while true do
    let line = input_line stdin in (
      step line;
    )
  done;
  None
with
  End_of_file -> None
;;

  
