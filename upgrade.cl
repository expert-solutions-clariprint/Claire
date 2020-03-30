// Sylvain Benilan
// cross compilation of claire
//	This file is used to add entities at step 1
// the complier implies we know the meta definition of new entities 

// updated Oct 2011

Core/RELEASE :: version()

reset_sym(self:string, m:module) : void ->	
	let s := get_symbol(m,self)
	in (put(value, s, unknown),
		put(module!, s, claire),
		put(mClaire/definition, s, m))

(begin(Kernel))
(end(Kernel))


(begin(Core))
(end(Core))


(begin(Language))
(end(Language))


(begin(Reader))
(end(Reader))


(begin(Generate))
(end(Generate))


(begin(Optimize))
(end(Optimize))


(begin(Serialize))
(end(Serialize))
