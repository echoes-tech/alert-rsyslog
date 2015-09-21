# Private class
class echoes_alert_rsyslog::firewall inherits echoes_alert_rsyslog {
  if $caller_module_name != $module_name {
    fail("Use of private class ${name} by ${caller_module_name}")
  }

  if $echoes_alert_rsyslog::manage_firewall {
    if defined('::firewall') {
      firewall { '100 allow Rsyslog access':
        port  => [ $echoes_alert_rsyslog::port ],
        proto => 'tcp',
        jump  => 'allowed',
      }->
      firewall { '100 allow Rsyslog access - IPv6':
        port     => [ $echoes_alert_rsyslog::port ],
        proto    => 'tcp',
        jump     => 'allowed',
        provider => 'ip6tables',
      }
    }
  }
}
