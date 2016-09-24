# Islandora Metadata Extras

## Introduction

Utility module that provides options for modifying how metadata is displayed and generated.

Currently, the following options are available:

* Metadata display
  * Replace collection PID with collection label in search results. See "Configuration," below for more details.
* Metadata generation
  * Adds an identifier element with type 'uuid' to all newly ingested MODS datastreams (via web forms and batch ingest). e.g.,```xml<identifier type="uuid">811f4f3f-7687-4b21-b1f3-6b547501b5ba</identifier>```

Modules that do related things include [Islandora Empty Metadata Values](https://github.com/mjordan/islandora_empty_metadata_values) and [Islandora Compound Parent Metadata](https://github.com/mjordan/islandora_compound_parent_metadata). These two modules may be folded into the Islandora Metadata Extras in the near future.

## Requirements

* [Islandora](https://github.com/Islandora/islandora)
* [Islandora Solr Search](https://github.com/Islandora/islandora_solr_search)
* To generate UUID, the Linux utility "uuidgen" must be installed (it is by defualt on most Linux systems)

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Configuration

Configuration options are available at Administration > Islandora > Islandora Utility Modules > Metadata Extras (`admin/islandora/tools/metadata_extras`).

* To use the option to replace the collection PID with its human-readable label:
  1. add the field that stores your objects' collecion PID to your Solr search results, just like you would for any other field. The name of this field is configured in Administration > Islandora> Solr Index > Solr Settings > Required Solr Fields > The isMemberOfCollection Solr field. The default values is "RELS_EXT_isMemberOfCollection_uri_ms".
  1. enable the option in the Metadata Extras admin options form. Note that not all Islandora objects are direct members of a collection; for example, children of compound objects, and newspaper and book pages.

## Maintainer

* [Mark Jordan](https://github.com/mjordan)

## Development and feedback

Pull requests are welcome, as are suggestions and use cases. In particular, if you have this module enabled and you are still seeing "empty" metadata elements, open a Github issue and include a URL to the object.

## License

* [GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
