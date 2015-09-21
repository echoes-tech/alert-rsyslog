# Private class
class echoes_alert_rsyslog::config inherits echoes_alert_rsyslog {
  if $caller_module_name != $module_name {
    fail("Use of private class ${name} by ${caller_module_name}")
  }

  $config_file     = '/etc/rsyslog.d/echoes-alert.conf'

  file { $config_file:
    ensure  => file,
    owner   => 0,
    group   => 0,
    mode    => '0600',
    content => template("${module_name}/${echoes_alert_rsyslog::branch}/${echoes_alert_rsyslog::version}/${config_file}.erb")
  }
}
