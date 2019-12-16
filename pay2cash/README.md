### Installation Instructions
	* Open src/map/clif.cpp and change function clif_parse_cashshop_open_request.
	* Create pay2cash table in your database.
	* Recompile your server.
	
### How it work
	* When player open cash shop system check his payments in table pay2cash.
	* If payments found server update his cash points.
	
### TODO
	* Write a module for FluxCP that can change donate to cash points.