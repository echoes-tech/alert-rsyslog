class echoes_alert_rsyslog (
  $branch          = $echoes_alert_rsyslog::params::branch,
  $cert_file       = $echoes_alert_rsyslog::params::cert_file,
  $install_dir     = $echoes_alert_rsyslog::params::install_dir,
  $manage_firewall = $echoes_alert_rsyslog::params::manage_firewall,
  $port            = $echoes_alert_rsyslog::params::port,
  $priv_key_file   = $echoes_alert_rsyslog::params::priv_key_file,
  $version         = $echoes_alert_rsyslog::params::version,
) inherits echoes_alert_rsyslog::params {
  validate_string($branch)
  validate_absolute_path($cert_file)
  validate_absolute_path($install_dir)
  validate_bool($manage_firewall)
  validate_integer($port, 65535, 1)
  validate_absolute_path($priv_key_file)
  validate_string($version)

  require echoes_alert_dbo

  anchor { "${module_name}::begin": } ->
  class { "${module_name}::install": } ->
  class { "${module_name}::config": } ->
  class { "${module_name}::firewall": } ->
  anchor { "${module_name}::end": }
}
