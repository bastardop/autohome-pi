<?php
/*
Copyright 2013 Anton Hammerschmidt

This file is part of PowerPi.

PowerPi is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

PowerPi is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with PowerPi.  If not, see <http://www.gnu.org/licenses/>.
*/

  session_start();
  include('./system.php');
	
  // Set Theme
  $app->Core->SetTheme();

  // Get Page and Action
  $page = $app->Secure->GetGET("page");
  $action = $app->Secure->GetGET("action");

  // Open Page
  $app->Nav->LoadPage($page, $action);

  // Apply Metatags
  $app->Meta->Invisible();
  $app->Meta->Apply();

  // Display Page
  $app->Tpl->Set('BASEDIR', _BASEDIR);
  $app->Tpl->Display();
?>
