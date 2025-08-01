#pragma once

#include "duckdb/catalog/catalog_entry/table_catalog_entry.hpp"

namespace duckdb {

class MooncakeTableMetadata;
class Moonlink;

class MooncakeTable : public TableCatalogEntry {
public:
	MooncakeTable(Catalog &catalog, SchemaCatalogEntry &schema, CreateTableInfo &info, Moonlink &moonlink,
	              uint32_t database_id, uint32_t table_id);

	~MooncakeTable();

	unique_ptr<BaseStatistics> GetStatistics(ClientContext &context, column_t column_id) override;

	TableFunction GetScanFunction(ClientContext &context, unique_ptr<FunctionData> &bind_data) override;

	TableStorageInfo GetStorageInfo(ClientContext &context) override;

	MooncakeTableMetadata &GetTableMetadata();

private:
	Moonlink &moonlink;
	uint32_t database_id;
	uint32_t table_id;
	mutex lock;
	unique_ptr<MooncakeTableMetadata> metadata;
};

} // namespace duckdb
