# echoes-alert-rsyslog

#### Table of Contents

1. [Overview](#overview)
2. [Module Description - What the module does and why it is useful](#module-description)
3. [Setup - The basics of getting started with wt](#setup)
    * [Setup requirements](#setup-requirements)
    * [Beginning with echoes_alert_rsyslog](#beginning-with-echoes_alert_rsyslog)
4. [Usage - Configuration options and additional functionality](#usage)
5. [Reference - An under-the-hood peek at what the module is doing and how](#reference)
6. [Limitations - OS compatibility, etc.](#limitations)
7. [Development - Guide for contributing to the module](#development)
8. [Contributors](#contributors)

## Overview

Puppet module to manage Rsyslog installation and configuration for Echoes Alert.

## Module Description

This module installs and configures Rsyslog for Echoes Alert.

## Setup

### Setup requirements

This module requires Wt to be installed.

You can use [echoes-wt](https://github.com/echoes-tech/puppet-wt) to install Wt.

The GUI resources (binaries, configuration files, etc.) should be located in the `files` or `templates` directories of the module, under the path `/$branch_name/$version_number/`.

### Beginning with echoes_alert_rsyslog

```puppet
include 'echoes_alert_rsyslog'
```

## Usage

An example of resource-like class declaration: 

```puppet
class {'echoes_alert_rsyslog':
  branch  => 'develop',
  version => 'latest',
}
```
## Reference

### Classes

#### Public classes

* echoes_alert_rsyslog: Main class, includes all other classes.

#### Private classes

* echoes_alert_rsyslog::params: Sets parameter defaults.
* echoes_alert_rsyslog::install: Handles the binary.
* echoes_alert_rsyslog::config: Handles the configuration.
* echoes_alert_rsyslog::firewall: Handles the firewall configuration.

#### Parameters

The following parameters are available in the `::echoes_alert_rsyslog` class:

##### `branch`

Tells Puppet which branch to choose to install GUI. Valid options: string. Default value: 'master'

##### `cert_file`

Specifies the certificate file to be used to launch the Wt server in https mode. Valid options: path. Default value: undef

##### `port`

Specifies the Rsyslog port. Valid options: integer >= 1. Default value: 443

##### `manage_firewall`

If true and if puppetlabs-firewall module is present, Puppet manages firewall to allow Rsyslog access for Echoes Alert. Valid options: 'true' or 'false'. Default value: 'false'

##### `priv_key_file`

Specifies the private key file to be used to launch the Wt server in https mode. Valid options: path. Default value: undef

##### `version`

Tells Puppet which version to choose to install GUI. Valid options: 'latest' or a specific version number. Default value: 'latest'

## Limitations

Debian family OSes is officially supported. Tested and built on Debian.

##Development

[Echoes Technologies](https://www.echoes-tech.com) modules on the Puppet Forge are open projects, and community contributions are essential for keeping them great.

## Contributors

The list of contributors can be found at: https://forge.echoes-tech.com/projects/rsyslog/repository/statistics#statistics-contributors

