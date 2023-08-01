export interface ReviewCreate{
    userHandle: string,
    productId: number,
    score: number,
    comment: string,
    postedDate: Date,
}