import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import { ProductScoreDTO } from '../dto/ProductScoreDTO';
import { environment } from 'src/environments/environment';
import { GenericPage } from '../model/GenericPage';
import { Product } from '../model/Product';
import { Review } from '../model/Review';
import { ProductCreate } from '../model/ProductCreate';
import { ProductScoreWithUserHandleDTO } from '../dto/ProductScoreWithUserHandleDTO';

@Injectable({
  providedIn: 'root'
})
export class ProductService {

  constructor(private http: HttpClient) { }

  getProductScoreWithUserHandles(pageNumber: number, pageSize: number, weight: number): Observable<GenericPage<ProductScoreWithUserHandleDTO>> {
    return this.http.get<GenericPage<ProductScoreWithUserHandleDTO>>(environment.apiURL + "/product-scores-with-users" + `?pageNumber=${pageNumber}` + `&pageSize=${[pageSize]}` + `&weight=${weight}`);
  }

  getProductScoreStatistic(pageNumber: number, pageSize: number): Observable<GenericPage<ProductScoreDTO>> {
    return this.http.get<GenericPage<ProductScoreDTO>>(environment.apiURL + "/products/sorted-by-reviews" + `?pageNumber=${pageNumber}` + `&pageSize=${[pageSize]}`);
  }

  getAllProducts(pageNumber: number, pageSize: number): Observable<GenericPage<Product>> {
    return this.http.get<GenericPage<Product>>(environment.apiURL + "/products" + `?pageNumber=${pageNumber}` + `&pageSize=${[pageSize]}`);
  }

  getAllProductsWithWeightFilter(pageNumber: number, pageSize: number, weight: number): Observable<GenericPage<Product>> {
    return this.http.get<GenericPage<Product>>(environment.apiURL + "/products/weight-filter" + `?pageNumber=${pageNumber}` + `&pageSize=${[pageSize]}` + `&weight=${weight}`);
  }

  getProductScorePageWithWeightFilter(pageNumber: number, pageSize: number, weight: number): Observable<GenericPage<ProductScoreDTO>> {
    return this.http.get<GenericPage<ProductScoreDTO>>(environment.apiURL + "/product-scores" + `?pageNumber=${pageNumber}` + `&pageSize=${[pageSize]}` + `&weight=${weight}`);
  }

  getAllReviewsForProduct(productId: number, pageNumber: number, pageSize: number): Observable<GenericPage<Review>> {
    return this.http.get<GenericPage<Review>>(environment.apiURL + "/products" + `/${productId}` + "/reviews" + `?pageNumber=${pageNumber}` + `&pageSize=${[pageSize]}`);
  }

  getProductById(id: number): Observable<Product> {
    return this.http.get<Product>(environment.apiURL + "/products/" + id.toString());
  }

  editProduct(product: Product): Observable<any>{
    return this.http.patch(environment.apiURL + "/products/" + product.id.toString(), product);
  }

  createProduct(product: ProductCreate): Observable<any>{
    return this.http.post(environment.apiURL + "/products", product);
  }

  deleteProduct(id: number): Observable<any> {
    return this.http.delete(environment.apiURL + "/products/" + id.toString());
  }
}
