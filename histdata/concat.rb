output = ""
Dir.glob("*.csv") {|file_name|
	data = File.read(file_name)
	puts file_name
	output = output + data.gsub(/;[^;]$/,",").gsub(/^.*;/,"")
}


output = "double gPriceTab[]={\n" + output + "\n};\n\nint gPriceTabSize = sizeof(gPriceTab)/sizeof(double);";
file = File.open("priceTab.cpp","w") 
file.write(output) 
file.close()

gets # <----