<?php
/**
 * @file
 * Default user block
 */
?>
<aside<?php print $attributes; ?>>
  <div<?php print $content_attributes; ?>>
    <?php
      global $base_url;
      if ($user->uid == 0) {
        print l(t('Log in'), 'user', array('query' => drupal_get_destination()));
        print ' or <a href="' . $base_url . '/user/register">Create a new account</a>';
      }
      else {
        print t('Welcome, !username! ', array('!username' => theme('username', array('account' => $user))));
        print l(t('Log out'), 'user/logout', array('attributes' => array('class' => array('logout'))));
      }
      print $content;
    ?>
  </div>
</aside>