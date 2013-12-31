<?php

class Config
{
  function Config()
  {
    // General
    $this->LANG = 'EN';
    $this->DOMAIN = '';
		$this->BASEDIR = '.';
		define('_BASEDIR', $this->BASEDIR);

    // Database
    $this->DB_ENABLED = false;
    $this->DB_HOST = 'localhost';
    $this->DB_USER = '';
    $this->DB_PASSWORD = '';
    $this->DB_DATABASE = '';  
    //SQLite DB File
    $this->DB_FILE = 'sqlite:/var/www/liteadmin/weather';

    // Template-Engine
    $this->TPL_DIR = './pages/';
    $this->TPL_TPLDIR = './pages/tpl/';
    $this->TPL_THEME = 'default';

    // Navigation
    $this->NAV_DEFAULT = _BASEDIR.'/index.php?page=home&action=list';
    $this->NAV_PAGES = array('home');

    // Meta
    $this->META_TITLE = 'PowerPi';
    $this->META_DESCRIPTION = 'Control your home';
    $this->META_KEYWORDS_EN = '';
    $this->META_KEYWORDS_DE = '';
    $this->META_AUTHOR = 'Anton Hammerschmidt';
  }
}  
?>
