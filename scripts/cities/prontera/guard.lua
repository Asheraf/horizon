local s = ...

s:mes("ABCDEF")
s:mes("GHIJKL")
s:next()
s:mes("MNOPQR")
s:mes("STUVWX")
s:next()
s:mes("masd")
s:mes("aaWX")
s:mes("asssOPQR")
s:mes("STssssWX")
s:next()
s:mes("MNddd")
s:mes("STUVWX")
s:mes("MNOPQR")
s:mes("STUVWX")
s:mes("MNOPQR")
s:mes("STUVWX")
local res = s:select("A", "B", "C")
s:next()
if res == 1 then
	s:mes("YO LOL")
elseif res == 2 then
	s:mes("Second option")
elseif res == 3 then
	s:mes("Third option")
end
s:next()
s:mes("MNOPQR")
s:mes("STUVWX")
s:close()

return s

