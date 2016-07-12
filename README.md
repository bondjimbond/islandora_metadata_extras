# Islandora Metadata Extras

## Introduction

Simple utility module that provides options for cleaning up or altering the way metadata elements render in Solr search results and object-level metadata displays.

Modules that do related things include [Islandora Empty Metadata Values](https://github.com/mjordan/islandora_empty_metadata_values) and [Islandora Compound Parent Metadata](https://github.com/mjordan/islandora_compound_parent_metadata). These two modules may be folded into the Islandora Metadata Extras in the near future.

## Requirements

* [Islandora](https://github.com/Islandora/islandora)
* [Islandora Solr Search](https://github.com/Islandora/islandora_solr_search)

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Configuration

Configuration options are available at Administration > Islandora > Islandora Utility Modules > Metadata Extras (`admin/islandora/tools/metadata_extras`). Currently, there is only one option, whether to replace the collection PID with its human-readable label or not in search results.

* To use this option, add the field that stores your objects' collecion PID to your Solr search results, just like you would for any other field. The name of this field is configured in Administration > Islandora> Solr Index > Solr Settings > Required Solr Fields > The isMemberOfCollection Solr field. The default values is "RELS_EXT_isMemberOfCollection_uri_ms".
  * Once you've added this field to your Solr search results, and enabled the option in Metadata Extras, the collection label will show up in search results. Note that not all Islandora objects are direct members of a collection; for example, children of compound objects, and newspaper and book pages.

## Maintainer

* [Mark Jordan](https://github.com/mjordan)

## Development and feedback

Pull requests are welcome, as are suggestions and use cases. In particular, if you have this module enabled and you are still seeing "empty" metadata elements, open a Github issue and include a URL to the object.

## License

* [GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
