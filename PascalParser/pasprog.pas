program QuadTest;
var a,b,c: real;
var d: integer;
var i: integer;
begin
	a := 10.0;
	b := 2.0;
	c := (a * b / 2 * (4 - 5)) + 20;
	i := 1;
	d := 0;
	if a < b then
		a := b;
	if a < b + 2 then
	begin
		a := b;
		b := c;
	end
	else
		b := a;
	while i < 30 do
		i := i + 1;
	repeat
		i := i - 1;
	until i = 0;
	for i := 1 to 20 do
		a := a + i;
	while a < 1 + d do
	begin
		repeat
		if b > 2 then
		begin
			for i := 1 to d+20 do
				a := a + i;
		end
		else
			a := 3000;
		until a > 2999;
		i:=5;
	end;
end.