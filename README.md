# Islandora Metadata Extras

## Introduction

Utility module that provides options for modifying how metadata is displayed and generated. Currently, the following options are available:

* Object metadata display
  * Hide metadata fields that contain no content.
  * Replace dates in yyyy-mm-dd and yyyy-mm format with human-readable equivalents like "September 24, 1968" and "September 1968".
* Search results
  * Hide metadata fields that contain no content.
  * Replace collection PID with collection label in search results.
  * Replace the values displayed in the search facet sidebar for selected Solr fields. Does not apply to Facet Pages.
  * Replace object namespace with an arbitrary string in search results, using an arbitrary Solr field.
* Embedded metadata
  * Add `<meta>` tags compatible with [Zotero](https://www.zotero.org/).
* Administrative metadata
  * Display datastream checksums (latest datastream version only).
  * Adds a "Solr Document" subtab under each object's Manage menu showing the object's Solr document in JSON format.
  * Display a tab containing a direct link to edit an object's metadata.
* Metadata generation
  * Adds an identifier element with type 'uuid' to all newly ingested MODS datastreams (via web forms and batch ingest). e.g.,`<identifier type="uuid">811f4f3f-7687-4b21-b1f3-6b547501b5ba</identifier>`.

None of these options, with the exception of the one in the "Metadata generation" group, modify your MODS or other sources of metadata, they simply change what is displayed to the end user. The only option that modifies your content is the one that adds a UUID to your MODS datastreams.

## Requirements

* [Islandora](https://github.com/Islandora/islandora)
* [Islandora Solr Search](https://github.com/Islandora/islandora_solr_search)
* To generate UUID, the Linux utility "uuidgen" must be installed (it is by defualt on most Linux systems)

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Configuration

Configuration options are available at Administration > Islandora > Islandora Utility Modules > Metadata Extras (`admin/islandora/tools/metadata_extras`).

* To hide metadata fields that contain no content:
  * Enable this option in the Metadata Extras admin options. No other configuration is necessary.
* To replace yyyy-mm-dd and yyyy-mm dates with human-readable equivalents in search results:
  * Enable this option in the Metadata Extras admin options. No other configuration is necessary. Conversion respects the current user interface language. Note that this option only applies if there is a single date the metadata field matching the pattern `\d\d\d\d\-\d\d\-\d\d` or `\d\d\d\d\-\d\d`.
* To replace the collection PID with its human-readable label:
  1. add the field that stores your objects' collecion PID to your Solr search results, just like you would for any other field. The name of this field is configured in Administration > Islandora> Solr Index > Solr Settings > Required Solr Fields > The isMemberOfCollection Solr field. The default values is "RELS_EXT_isMemberOfCollection_uri_ms".
  1. enable the option in the Metadata Extras admin options form. Note that not all Islandora objects are direct members of a collection; for example, children of compound objects, and newspaper and book pages.
* To rewrite the text of facet values in the search sidebar:
  1. Enable this option in the Metadata Extras admin options.
  2. Enter the Solr field whose values you wish to rewrite. It must be one of your configured facet fields.
  3. Enter the values you expect, followed by the pipe "|" character, and the values you wish to replace them with.
* To add `<meta>` tags containing Dublin Core metadata:
  * Enable this option in the Metadata Extras admin options. No other configuration is necessary. This module provides a hook that allows other modules to alter the metadata before it is added to the page markup. See islandora_metadata_extras.api.php for more information.
* To display datastream checksums within an object's Manage > Datastreams tab:
  * Enable this option in the Metadata Extras admin options. No other configuration is necessary, but unless you have enabled checksums on your datastreams, for example, using the [Islandora Checksum](https://github.com/Islandora/islandora_checksum) module, no checksums will be displayed. Note that only the checksum for the current version of the datastream is displayed.
* To display the "Solr Document" subtab, enable that option. Users must have "Manage object properties" permission to see this subtab.
* To display the "Edit metadata" tab, enable that option. User must have "Edit metadata" permission to see this tab. If an object doesn't have one of the specified datastreams, an error message to that effect displays when this tab is clicked. If it has one of the datastreams but the relevant solution pack does not provide an "edit" link in the datastreams list, a generic "There are no edit methods specified for this datastream" message appears when this tab is clicked.
* To add an identifier element containing a UUID to your MODS datastreams:
  * Enable this option in the Metadata Extras admin options. No other configuration is necessary.

## Maintainer

* [Brandon Weigel](https://github.com/bondjimbond)
    * Former maintainer: [Mark Jordan](https://github.com/mjordan)

## Development and feedback

Bug reports, use cases, feature requests, and pull requests are welcome. Please see the CONTRIBUTING.md file for more information.

## License

* [GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
