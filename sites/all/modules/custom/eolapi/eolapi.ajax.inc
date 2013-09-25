<?php

/**
 * Callback function.  This will help to populate an empty view.
 * @todo investigate whether view-name has usage defined by views modules and the
 *       effect of using viewName.
 */
function eolapi_callback(){
  $callbacks = module_invoke_all('eolapi_callbacks');
  if(isset($callbacks[$_POST['viewName']])){
    call_user_func($callbacks[$_POST['viewName']], $_POST['tid']);
  }else{
    module_load_include('functions.inc', 'eolapi');
    eolapi_search($_POST['tid']);
  }
  $view = views_get_view($_POST['viewName']);
  $view->args[] = $_POST['tid'];
  $output = $view->render('block');
  if(count($view->result)){
    echo $output;
  }else{
    echo "";
  }
}