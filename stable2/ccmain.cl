// *******************************************************************
// * CLAIRE                                                          *
// * ccmain.cl                                                       *
// * Copyright (C) 1994 - 2003 Yves Caseau. All Rights Reserved      *
// * cf. copyright info in file object.cl: about()                   *
// *******************************************************************
// * Sylvain Benilan                                                 *
// * this file has been highly modified for the xl version           *
// *******************************************************************

[main(l:list) : void ->
	PRODUCER.Generate/extension := Id(PRODUCER.Generate/extension),
	compiler.libraries_dir := Id(compiler.libraries_dir),
	compiler.libraries := Id(compiler.libraries), //<sb> v3.3.33
	compiler.headers_dir := Id(compiler.headers_dir),
	compiler.source := Id(compiler.source),
	compiler.options := Id(compiler.options),
	compiler.env := Id(compiler.env),
	so_options  := Id(so_options),
  cxx_options := Id(cxx_options),
  ld_options  := Id(ld_options)]
