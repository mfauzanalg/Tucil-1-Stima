procedure TForm1.ConvexHull( ap: array of TPoint );
var
 
  pi                : array of integer;
  hull              : array of integer;
  h, i, j, k, l     : integer;
  dx, dy, dx2, dy2  : integer;
  found             : boolean;
begin
  { initialize index } 
  setlength( pi, length( ap ) );
  for i := 0 to high( pi ) do
    pi[i] := i;
 
  { sort the index lexicographically, shown here using simple quadratic complexity sort algorithm }
  for i := 0 to high( pi ) - 1 do begin
    for j := i + 1 to high( pi ) do begin
      if ( ap[pi[j]].X < ap[pi[i]].X ) or ( ( ap[pi[j]].X < ap[pi[i]].X ) and ( ap[pi[j]].Y > ap[pi[i]].Y ) ) then begin
        k := pi[j];
        pi[j] := pi[i];
        pi[i] := k;
      end;
    end;
  end;
 
  { build upper boundary }
  setlength( hull, 2 );
  hull[0] := pi[0];
  hull[1] := pi[1];
  h := 1;
 
  for i := 2 to high( pi ) do begin
    found := false;
    for k := 1 to high( hull ) do begin
      dx := ap[hull[k]].X - ap[hull[k - 1]].X;
      dy := ap[hull[k]].Y - ap[hull[k - 1]].Y;
 
      dx2 := ap[pi[i]].X - ap[hull[k]].X;
      dy2 := ap[pi[i]].Y - ap[hull[k]].Y;
 
      j := dy * dx2 - dx * dy2;
      { delete previous non-convex edge w.r.t current point }
      if j > 0 then begin
        hull[k] := pi[i];
        setlength( hull, k + 1 );
        found := true;
        break;
      end;
    end;
 
    { add if current point lies on the right side of previous upper edges }
    if not found then begin
      setlength( hull, length( hull ) + 1 );
      hull[high( hull )] := pi[i];
    end;
  end; 
 
  { build lower boundary }
  h := high( hull ) - 1;
  for i := high( pi ) downto 0 do begin
    found := false;
    for k := h to high( hull ) do begin
      dx := ap[hull[k]].X - ap[hull[k - 1]].X;
      dy := ap[hull[k]].Y - ap[hull[k - 1]].Y;
 
      dx2 := ap[pi[i]].X - ap[hull[k]].X;
      dy2 := ap[pi[i]].Y - ap[hull[k]].Y;
 
      j := dy * dx2 - dx * dy2;
      if j > 0 then begin
        hull[k] := pi[i];
        setlength( hull, k + 1 );
        found := true;
        break;
      end;
    end;
 
    if not found then begin
      setlength( hull, length( hull ) + 1 );
      hull[high( hull )] := pi[i];
    end;
  end;
 
  { display result }
  Image1.Canvas.Pen.Color := clLime;
  Image1.Canvas.MoveTo( ap[hull[0]].X, ap[hull[0]].Y );
  for i := 1 to high( hull ) do
    Image1.Canvas.LineTo( ap[hull[i]].X, ap[hull[i]].Y );
  for i := 0 to high( hull ) do
    drawpt( ap[hull[i]].X, ap[hull[i]].Y, clRed );
   
end;