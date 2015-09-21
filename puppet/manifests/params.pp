# == Class: echoes_alert_rsyslog::params
#
# This is a container class with default parameters for echoes_alert_rsyslog classes.
class echoes_alert_rsyslog::params {
  $name = 'rsyslog'

  $branch          = 'master'
  $cert_file       = undef
  $install_dir     = "/opt/echoes-alert/${name}"
  $port            = 443
  $manage_firewall = false
  $priv_key_file   = undef
  $version         = 'latest'

  $binary_path = "${install_dir}/bin"
  $config_path = "${install_dir}/etc"
}
