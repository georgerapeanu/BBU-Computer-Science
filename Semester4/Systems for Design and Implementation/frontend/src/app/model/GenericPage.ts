export interface GenericPage<T> {
    content: T[],
    totalPages: number,
    pageable: {
        pageNumber: number,
        pageSize: number
    }
}