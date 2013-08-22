-- SUMMARY --

Chosen uses the Chosen jQuery plugin to make your <select> elements more user-friendly.


-- INSTALLATION --

  1. Download the Chosen jQuery plugin (http://harvesthq.github.com/chosen/ version 1.0 is recommended) and extract the file under sites/all/libraries.
  2. Download and enable the module.
  3. Configure at Administer > Configuration > User interface > Chosen (requires administer site configuration permission)


-- INSTALLATION WITH MAKE FILE --

If you have drush make installed, you can use the chosen.make file to download the recommended version of chosen.
	1. drush make sites/all/modules/chosen/chosen.make --no-core
	2. drush en chosen -y


-- ACCESSIBILITY CONCERN --

There are accessibility problems with the main library as identified here:
	https://github.com/harvesthq/chosen/issues/264
