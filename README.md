# Islandora Metadata Extras

## Introduction

Utility module that provides options for modifying how metadata is displayed and generated. Currently, the following options are available:

* Object metadata display
  * Hide metadata fields that contain no content.
  * Replace dates in yyyy-mm-dd and yyyy-mm format with human-readable equivalents like "September 24, 1968" and "September 1968".
* Search results
  * Hide metadata fields that contain no content.
  * Replace collection PID with collection label in search results.
* Embedded metadata
  * Add `<meta>` tags compatible with [Zotero](https://www.zotero.org/)
* Metadata generation
  * Adds an identifier element with type 'uuid' to all newly ingested MODS datastreams (via web forms and batch ingest). e.g.,`<identifier type="uuid">811f4f3f-7687-4b21-b1f3-6b547501b5ba</identifier>`
  * Use an XSLT stylesheet other the one shipped with Islandora ([from the Library of Congress](http://www.loc.gov/standards/mods/v3/MODS3-5_DC_XSLT1-0.xsl)) to generate DC datastreams from MODS datastreams.

## Requirements

* [Islandora](https://github.com/Islandora/islandora)
* [Islandora Solr Search](https://github.com/Islandora/islandora_solr_search)
* To generate UUID, the Linux utility "uuidgen" must be installed (it is by defualt on most Linux systems)

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Configuration

Configuration options are available at Administration > Islandora > Islandora Utility Modules > Metadata Extras (`admin/islandora/tools/metadata_extras`).

* To use the options to hide metadata fields that contain no content:
  * Enable these options in the Metadata Extras admin options. No other configuration is necessary.
* To use the option to replace yyyy-mm-dd and yyyy-mm dates with human-readable equivalents in search results:
  * Enable this option in the Metadata Extras admin options. No other configuration is necessary. Conversion respects the current user interface language. Note that this option only applies if there is a single date the metadata field matching the pattern `\d\d\d\d\-\d\d\-\d\d` or `\d\d\d\d\-\d\d`.
* To use the option to replace the collection PID with its human-readable label:
  1. add the field that stores your objects' collecion PID to your Solr search results, just like you would for any other field. The name of this field is configured in Administration > Islandora> Solr Index > Solr Settings > Required Solr Fields > The isMemberOfCollection Solr field. The default values is "RELS_EXT_isMemberOfCollection_uri_ms".
  1. enable the option in the Metadata Extras admin options form. Note that not all Islandora objects are direct members of a collection; for example, children of compound objects, and newspaper and book pages.
* To use the option to add an identifier element containing a UUID to your MODS datastreams:
  * Enable this option in the Metadata Extras admin options. No other configuration is necessary.
* To use an alternative XSLT stylesheet to generate DC datastreams from MODS datastreams, check the "Use a custom XSLT stylesheet to create DC datastreams." option and upload an XLST file.
  * After you enable this function, all DC datastreams on objects that are ingested or modified will be generated using your custom XSLT stylesheet.

## Maintainer

* [Mark Jordan](https://github.com/mjordan)

## Development and feedback

Pull requests are welcome, as are suggestions and use cases. Please open an issue before opening a pull request.

## License

* [GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
