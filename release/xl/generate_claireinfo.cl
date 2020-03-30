
(let fin := fopen("release" / "xl" / "claireinfo.xml.in", "r"),
		fout := fopen("public" / "xl" / "claireinfo.xml", "w")
in (while not(eof?(fin))
		let tmp := fread(fin, 1024)
		in fwrite(replace(tmp, "@@version@@", "v" /+ release()), fout),
	fclose(fin),
	fclose(fout)))
