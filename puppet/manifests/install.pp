# Private class
class echoes_alert_rsyslog::install inherits echoes_alert_rsyslog {
  if $caller_module_name != $module_name {
    fail("Use of private class ${name} by ${caller_module_name}")
  }

  require openssl
  require echoes_alert_dbo

  class { '::rsyslog':
    gnutls => true,
  }


  file { $echoes_alert_rsyslog::install_dir:
    ensure => 'directory',
    owner  => 0,
    group  => 0,
    mode   => '0755'
  }->
  file { $echoes_alert_rsyslog::binary_path:
    ensure => 'directory',
    owner  => 0,
    group  => 0,
    mode   => '0755'
  }->
  file { "${echoes_alert_rsyslog::binary_path}/${echoes_alert_rsyslog::service_name}":
    ensure => 'file',
    owner  => 0,
    group  => 0,
    mode   => '0755',
    source => "puppet:///modules/${module_name}/${echoes_alert_rsyslog::branch}/${echoes_alert_rsyslog::version}/rsyslog",
  }

  file { $echoes_alert_rsyslog::config_path:
    ensure => 'directory',
    owner  => 0,
    group  => 0,
    mode   => '0755'
  }->
  file { "${echoes_alert_rsyslog::config_path}/${echoes_alert_rsyslog::service_name}.conf":
    ensure => 'file',
    owner  => 0,
    group  => 0,
    mode   => '0644',
    source => "puppet:///modules/${module_name}/${echoes_alert_rsyslog::branch}/${echoes_alert_rsyslog::version}/conf/ea-parser.conf.erb",
  }

  file { '/var/log/parser.log':
    ensure => 'file',
    owner  => 0,
    group  => 0,
    mode   => '0644'
  }
}
