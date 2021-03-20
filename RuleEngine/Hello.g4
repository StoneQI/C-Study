grammar hello;
s  : object ;         // match keyword hello followed by an identifier
object: '{' ID ':' value (',' ID ':' value )*'}';
value : ID | object;
ID : [a-z]+ ;             // match lower-case identifiers
WS : [ \t\r\n]+ -> skip ; // skip spaces, tabs, newlines