Test data
=========

The files testdata1, 2, 3 and 4 contain 240 points generated as if from a gaussian mixture model with 
3 mixture components with relative probabilities 10:8:6 (in fact I just generated 100, 80 and 60 points 
exactly from three different gaussians).

Note that the files were generated in Windows so you may need som care when reading the text because of 
incompatibility between text formats in unix and windows (eg CRLF vs LF for newlines)

testdata1.txt 

	Points are well separated and sorted (so you can check). The first 100 come from one cluster, the 
	next 80 from another and the final 60 from a third.

testdata2.txt

	Points not so well separated but sorted

testdata3.txt

	Points not so well separated and unsorted (same data as testdata2)

testdata4.txt

	Strong overlap between classes in the point samples

gentestdata.m

	The matlab script used to generate the data (so you can generate more if you want)
  