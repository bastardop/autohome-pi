<?php

class Database
{
  var $app;
  var $db;
  var $bpp_stmt;

  function Database(&$app)
  {
    $this->app = $app;
    
    if($this->app->Conf->DB_ENABLED)
    $this->db = new mysqli($app->Conf->DB_HOST, $app->Conf->DB_USER,
                           $app->Conf->DB_PASSWORD, $app->Conf->DB_DATABASE);
                      
    if($this->db->connect_error!='')
    {
      echo 'ERROR: Can\'t connect to Database.<br>';
      exit;
    }  
  }

  function __destruct()
  {
    if($this->bpp_stmt!=null) $this->bpp_stmt->close();
    $this->db->Close();
  }

  function Select($query)
  {
    $result = '';
    $stmt = $this->db->prepare($query);
    
    if($stmt === false)
      echo 'ERROR: Can\'t process Query<br>';
    else
    {
      if($stmt->field_count == 1)
      {
        $stmt->execute();
        $stmt->bind_result($result);
        $stmt->fetch();
        $stmt->close();
      }else
        echo 'ERROR: Wrong Field-Count<br>';
    }
    
    return $result;
  }

  function SelectArr($query)
  {
    $stmt = $this->db->prepare($query);
    
    if($stmt === false)
      echo 'ERROR: Can\'t process Query<br>';
    else
    {
      $stmt->execute();
      $meta = $stmt->result_metadata();
      
      while ($field = $meta->fetch_field()) {
        $var = $field->name; 
        $$var = null; 
        $parameters[$field->name] = &$$var; 
      } 

      call_user_func_array(array($stmt, 'bind_result'), $parameters); 
          
      while($stmt->fetch())
      {
				foreach($parameters as $key=>$value)
	  			$arr[$key] = $value;
				$result[] = $arr;
      }

      $stmt->close();

      return $result;
    }
    return '';
  }

  function Query($query)
  {
    if($this->bpp_stmt!='')
      $this->bpp_stmt->close();

    $this->bpp_stmt = $this->db->prepare($query);
  }

  function Put($types)
  {
    $args = func_get_args();
    $args_count = func_num_args();
    
    if($args_count < 2)
    {
      echo 'ERROR: Invalid Argument-Count';
      exit;
    }

    if($this->bpp_stmt == null || $this->bpp_stmt=='')
    {
      echo 'ERROR: Bad Put<br>';
      return;
    }

    $bind_names[] = $types;

    for ($i=0; $i<count($args)-1;$i++) {
      $bind_name = 'bind' . $i; 
      $$bind_name = $args[$i+1];
      $bind_names[] = &$$bind_name;
    }

    call_user_func_array(array($this->bpp_stmt,'bind_param'),$bind_names);
    
    $this->bpp_stmt->execute();
  }

  function UploadBlob($data)
  {
    if(!($this->bpp_stmt == null || $this->bpp_stmt==''))
    {
      $null = NULL;
      $this->bpp_stmt->bind_param('b', $null);
      $this->bpp_stmt->send_long_data(0, $data);
      $this->bpp_stmt->execute();
    }
  }

  function InsertID()
  {
    return $this->db->insert_id;
  }

  function Error()
  {
    echo $this->db->error;
  }
}

?>
